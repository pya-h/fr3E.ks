import Keys from "./keys";
import io from "./io";
import { Field } from "./protos";
export default class Memento {
    fields: { [key: string]: Field };
    whatevers: { [key: string]: any };
    methods: { [key: string]: any };
    samples: { [key: string]: any };
    $: io;

    // THINK:
    // Define each type as a class?
    constructor($io: io) {
        this.fields = {};
        this.whatevers = {}; // same as objects
        this.methods = {};
        this.samples = {}; // classes [meanings?]

        this.$ = $io;
    }

    define = {
        field: (key: string, value: any) => {
            this.fields[key] = isNaN(value)
                ? Field.Whatever(value)
                : Field.Numeric(value);
        },
    };

    recognize = (key: any) => {
        if (!isNaN(key)) return { type: "scalar", value: +key };

        if (key[0] === Keys.Read) {
            const fieldName = key.slice(1);
            const value = this.$.ask();
            if (fieldName) this.fields[fieldName] = Field.Numeric(value);
            return this.fields[fieldName]; // edit type
        }
        // Better to define classes for fields, etc
        if (key in this.fields) return this.fields[key];

        // and this for methods and etc
        return Field.Literal(key); // nothing field
    };
}
