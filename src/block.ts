import Line from './line';

export default
class Block {
    lines: Line[];

    constructor() {
        this.lines = []; // line's block
    }

    next = (line: Line) => { this.lines.push(line) };
}
