import Block from "./block";
import Line from "./line";
import $ from "./$";

import Keys from "./keys";

export default class Analyst {
    private mainblock: Block;

    constructor() {
        this.mainblock = new Block();
    }

    run = (script: string = '') => {
        // when running script you can save results on console on a file too > t.txt
        while (true) {
            const newline: Line = new Line($.ask());
            let expression = newline.extract();
            
            this.mainblock.next(expression);
        }
    };
}
