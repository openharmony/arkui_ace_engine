export declare namespace uiObserver {
    export class DensityInfo {
        density: number;
    }
    type Callback<T,V = void> = (data: T) => V
      
    export interface UIObserver {
        on(type: string, callback: () => void): void;
        on(type:'densityUpdate',callback:Callback<DensityInfo>): void;
        off(type: string, callback?: () => void): void;
    }
    export function createUIObserver(id: number): UIObserver;
}
