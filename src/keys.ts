const Operators = {
    Add: "+",
    Multiply: "*",
    Devide: "%",
    Substract: "-",
    Raise: "^",
    Root: "_/",
};

const Keys = {
    isOperator: (key: string) => Object.values(Keys.Operators).includes(key),
    Operators,
    TextSign: ":",
    Bye: "<3",
    Write: "#",
    Read: "?", // ?x ?y
    ExactWord: '`' // this key prevents fields from being overwritten by their value in texts
};

export default Keys;