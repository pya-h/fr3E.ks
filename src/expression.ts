import Memento from "./memento";

export default
class Expression {
    memento: Memento;
    words: string[];

    constructor(words: string[], memento: Memento) {
        this.words = words;
        this.memento = memento;
    }

    decipher = () => {
        const { words, memento } = this;

        for (let i = 0; i < words.length; i++) {
            if (!isNaN(memento.recognize(words[i]).data)) {
                // means words[0] is numeric
                // every time starts calculations at i and goes on to end of math operations at j
                // then final result will replace the words array item from i to j

            }
        }
        // now words is ready to be defined as scalar or array or sth
        // ex: fial words === 2 3 4 => array
        // ex: final words === 45 => scalar
        // ex: final words === whatever
    }
}
