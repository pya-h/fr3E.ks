import Expression from './expression';

export default
class Line {

    static extract = (code: string) => new Expression(code.split(/ /).filter((el) => el));

    // decipher = () => {
    //     const words = this.code.split(/ /)
    //         .filter((el) => el);

    //     switch (words[0]) {
    //         default: return "error";
    //     }
    // }
}
