export const Inspector: any = undefined

export interface ComponentObserver {
    on(type: string, callback: ()=>void) : void;
    off(type: string, callback?: ()=>void) : void;
}