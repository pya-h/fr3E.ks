const Operators = {
    Add: "+",
    Multiply: "*",
    Devide: "%",
    Substract: "-",
    Raise: "^",
    Root: "_/"
};

const Keys = {
    Operators,
    isOperator: (key: string) => Object.values(Keys.Operators).includes(key),
    Bye: "<3",
    Write: "#",
    Read: "?", // ?x ?y
};

export default Keys;
