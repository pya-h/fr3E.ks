// prototypes

class Field {
    type: string;
    value: any;

    constructor(type: string = "nothing", value: any = undefined) {
        this.type = type;
        this.value = value;
    }

    static Numeric = (value: any) => new Field("numeric", +value);
    static Nothing = () => new Field("nothing", undefined);
    static Whatever = (value: any) => new Field("whatever", value);

    static Literal = (value: any) => new Field("literal", value);
}

export {
    Field
}