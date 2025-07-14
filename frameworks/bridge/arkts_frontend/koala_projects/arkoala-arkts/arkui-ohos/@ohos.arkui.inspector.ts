declare namespace inspector {
    export interface ComponentObserver {
        on(type: 'layout' | 'draw', callback: () => void): void;
 
        off(type: 'layout' | 'draw', callback?: () => void): void;
    }
    export function createComponentObserver(id: string): ComponentObserver;
}
export default inspector;