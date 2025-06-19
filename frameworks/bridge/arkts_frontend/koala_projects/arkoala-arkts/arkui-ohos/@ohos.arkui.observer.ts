export declare namespace uiObserver {
    export class DensityInfo {
        density: number;
    }
    type Callback<T,V = void> = (data: T) => V
      
    export interface UIObserver {
        on(type: string, callback: object): void;
        off(type: string, callback?: object): void;
    }
    export function createUIObserver(id: number): UIObserver;
}
