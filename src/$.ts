import PromptSync from 'prompt-sync';
import chalk from 'chalk';

export default class $ {
    public static cache: string =  "Nada!";
    private static prompt: PromptSync.Prompt = PromptSync();

    static ask = (question = "") => $.cache = $.prompt(`> ${question}`);

    static echo = (text: string) => { console.log(chalk.green(text !== undefined ? text : $.cache)); }
        // recall = () => { console.log(io.cache); }

    static siktir = () => {
        /*for (const field of Object.keys(this))
            delete this[field];
        return this;*/
    }
}
