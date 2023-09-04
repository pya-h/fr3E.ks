import Block from "./block";
import Line from "./line";
import io from "./io";
import Memento from "./memento";
import Expression from "./expression";
import Keys from "./keys";

export default class Analyst {
    mainblock: Block;
    memento: any;

    constructor() {
        this.mainblock = new Block();
        this.memento = undefined;
    }

    processArray = (arr: string[], start = 0, end = arr.length - 1) => {
        let s = "";
        for (let i = start; i <= end; i++)
            s += this.memento.recognize(arr[i]).value + " ";
        return s;
    };

    decipher = (expression: Expression) => {
        const { memento } = this;
        let values: any[] = [];
        const { words } = expression;
        // start processing words in expression
        for (let pos = 0; pos < words.length; pos++) {
            let i = pos + 1;
            const { type, value } = this.memento.recognize(words[pos]);
            if (!isNaN(value)) {
                let r = value;
                // calculate any math expression before reaching next term
                for (; i < words.length && Keys.isOperator(words[i]); i++) {
                    const { type, value } = memento.recognize(words[i + 1]);
                    if (!isNaN(value)) {
                        // means words[0] is numeric
                        // every time starts calculations at pos and goes on to end of math operations at i
                        switch (words[i]) {
                            case Keys.Operators.Add:
                                r += value;
                                break;
                            case Keys.Operators.Substract:
                                r -= value;
                                break;
                            case Keys.Operators.Multiply:
                                r *= value;
                                break;
                            case Keys.Operators.Devide:
                                r /= value;
                                break;
                            case Keys.Operators.Raise:
                                r **= value;
                                break;
                            case Keys.Operators.Root:
                                // its better to handle this one outside
                                // so that it can handle other roots, and cascade rooting as well
                                r *= (value ** 0.5);
                                break;
                            default:
                                throw new Error("where the fuck did you learn math fucker?")
                        }
                        i++;
                    } else break;
                }
                values.push(r); // the line may have seperated array items, so this algo calculates each expression
                // and return all at once
            }
            pos = i - 1;
            // now expression.words is ready to be defined as scalar or array or sth
            // ex: fial expression.words === 2 3 4 => array
            // ex: final expression.words === 45 => scalar
            // ex: final expression.words === whatever
        }
        return values.length === 1 ? values[0] : values;
    };

    run = () => {
        const $ = new io();
        this.memento = new Memento($);
        while (true) {
            const newline: Line = new Line($.ask());
            const expression = newline.extract();
            switch (expression.words[0]) {
                case Keys.Write:
                    // for now
                    let s = this.processArray(expression.words, 1);
                    $.echo(s);
                    break;
                case Keys.Bye:
                    $.echo("bye dickhead!");
                    return 0;
                default:
                    // words[1:end] will be sent to another method to be calculated and processed
                    const first: any = expression.words.splice(0, 1)[0];
                    const next = this.decipher(expression);
                    if (isNaN(first)) this.memento.define.field(first, next);
                    else $.echo(first + next);
            }
            // THINK:***
            // use Line in blocks? or Expression?
            this.mainblock.next(expression);
        }
    };
}
