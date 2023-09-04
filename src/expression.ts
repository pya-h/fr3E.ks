
export default class Expression {
    words: any[];

    constructor(words: any[]) {
        this.words = words;
    }

    take = (from: number, until = -1) => 
        // take words: from -> until
        new Expression(this.words.slice(from, until >= 0 ? until : this.words.length));
    
}
