import Expression from './expression';
import Keys from './keys';

export default
class Block {
    statements: Expression[];

    constructor() {
        this.statements = []; // Expression's block
    }

    get line() {
        return this.statements;
    }
    
    at = (lineNumber: number) => this.statements[lineNumber];

    next = (expression: Expression) => { 
        this.statements.push(expression)
        if(expression.words[0] === Keys.LineAt)
                this.executeLine(+expression.words[1]);
                // $ 1 * 10 => run li e n times
                // if line at n is a block(like a lool) * 4 => loop in loop
                // $ n + statement => add expression to line
        expression.execute();
    };

    extract = (script: string) => {
        
    }
    execute = () => {
        // run whole
    }
    executeLine = (statementIndex = -1) => {
        if(statementIndex > this.statements.length)
            throw new Error("a'int is no such line you idiot!");
        this.at(statementIndex === -1 ? this.statements.length - 1 : statementIndex).execute();
    }
}
