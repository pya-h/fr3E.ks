import Expression from './expression';

export default
class Line {
    code: string;
    block: [];

    constructor(code: string) {
        this.code = code;
        this.block = [];
    }

    extract = () => new Expression(this.code.split(/ /).filter((el) => el));

    // decipher = () => {
    //     const words = this.code.split(/ /)
    //         .filter((el) => el);

    //     switch (words[0]) {
    //         default: return "error";
    //     }
    // }
}
