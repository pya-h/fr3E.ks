import Expression from './expression';
import Keys from './keys';
import fs from 'fs';
import Line from './line';
export default
class Block {
    statements: any[];

    constructor(statements: Expression[] = []) {
        this.statements = statements; // Expression's block
        // deafult []param must cause reference error like in python?
    }

    get line() {
        return this.statements;
    }
    
    nextScript = (scriptName: string) => {
        const script: string = fs.readFileSync(scriptName).toString();
        const block = new Block(
            script.split(/[\n\r]/).map(line => Line.extract(line))
        );
        this.statements.push(block);
        block.execute();
    }
    at = (lineNumber: number) => this.statements[lineNumber];

    nextExecutioner = (expression: any) => {
        if(!(expression instanceof Expression))
            return false;
        if(expression.words[0] === Keys.LineAt) {
            this.executeLine(+expression.words[1]);
            return true;
        }
        if(expression.words[0] === Keys.RunScript) {
            this.nextScript(expression.words[1]);
            
            return true;
        }
                // $ 1 * 10 => run li e n times
                // if line at n is a block(like a lool) * 4 => loop in loop
                // $ n + statement => add expression to line
        return false;
    }
    next = (expression: Expression) => { 
        if(!this.nextExecutioner(expression)) {
            expression.execute();
            this.statements.push(expression);
        }
    };

    execute = () => 
        // BUG: second run script creates new block every time
        // run whole
        this.statements.forEach((statement, _) => !this.nextExecutioner(statement) && statement.execute());
    
    executeLine = (statementIndex = -1) => {
        if(statementIndex > this.statements.length)
            throw new Error("a'int is no such line you idiot!");
        this.at(statementIndex === -1 ? this.statements.length - 1 : statementIndex).execute();
    }
}
