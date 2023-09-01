import Block from './block';
import Line from './line';
import io from './io';
import Memento from './memento';
import Expression from './expression';
import Keys from './keys';

export default class Analyst {
    mainblock: Block;
    memento: any;

    constructor() {
        this.mainblock = new Block();
        this.memento = undefined;

    }

    processArray = (arr: string[], start = 0, end = arr.length - 1) => {
        let s = '';
        for (let i = start; i <= end; i++) s += this.memento.recognize(arr[i]).data + " ";
        return s;
    }

    run = () => {
        const $ = new io();
        this.memento = new Memento($);
        while (true) {
            const newline: Line = new Line($.ask());
            const words = newline.extract();
            switch (words[0]) {
                case Keys.Write:
                    // for now
                    let s = this.processArray(words, 1);
                    $.tell(s);
                    break;
                case Keys.Bye:
                    $.tell("bye dickhead!");
                    return 0;
                default:
                    // words[1:end] will be sent to another method to be calculated and processed
                    const first: any = words[0];
                    words.splice(0, 1);
                    const next = new Expression(words, this.memento).decipher();
                    if (isNaN(first))
                        this.memento.define.field(first, next);
                    else
                        $.tell(first + next);
            }

            this.mainblock.next(newline);
        }
    }
}
