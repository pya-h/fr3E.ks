import Keys from "./keys";
import io from "./io";

export default class Memento {
    fields: { [key: string]: any };
    whatevers: { [key: string]: any };
    methods: { [key: string]: any };
    samples: { [key: string]: any };
    $: io;

    constructor($io: io) {
        this.fields = {};
        this.whatevers = {}; // same as objects
        this.methods = {};
        this.samples = {}; // classes [meanings?]

        this.$ = $io;
    }

    define = {
        field: (key: string, value: any) => {
            this.fields[key] = isNaN(value) ? value : +value;
        },
    };

    recognize = (key: any) => {
        if (!isNaN(key)) return { type: "scalar", value: +key };
        
        if (key[0] === Keys.Read) {
            const fieldName = key.slice(1);
            const value = this.$.ask();
            if (fieldName) this.fields[fieldName] = value;

            return { type: "field", value };
        }
        if (key in this.fields)
            return { type: "field", value: this.fields[key] };
        //and this for methods and etc
        return { type: "None", value: key };
    };
}
