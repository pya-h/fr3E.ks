import PromptSync from 'prompt-sync';
import chalk from 'chalk';

export default class io {
    cache: string;
    prompt: PromptSync.Prompt;

    constructor() {
        this.cache = "Nada!";
        this.prompt = PromptSync();
    }

    ask = (question = "") => this.cache = this.prompt(`> ${question}`);

    tell = (text: string) => { console.log(chalk.green(text !== undefined ? text : this.cache)); }
        // recall = () => { console.log(this.cache); }

    siktir = () => {
        /*for (const field of Object.keys(this))
            delete this[field];
        return this;*/
    }
}
