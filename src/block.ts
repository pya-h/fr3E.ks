import Expression from './expression';

export default
class Block {
    statements: Expression[];

    constructor() {
        this.statements = []; // Expression's block
    }

    next = (Expression: Expression) => { this.statements.push(Expression) };
}
