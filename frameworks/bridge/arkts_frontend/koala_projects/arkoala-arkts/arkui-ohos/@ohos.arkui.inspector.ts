declare namespace inspector {
    export interface ComponentObserver {
        on(type: 'layout' | 'draw', callback: () => void): void;
 
        off(type: 'layout' | 'draw', callback?: () => void): void;
    }
    export function createComponentObserver(id: string): ComponentObserver;
    export function getFilteredInspectorTree(filters?: Array<string>): string;
    export function getFilteredInspectorTreeById(id: string, depth: number, filters?: Array<string>): string;
}
export default inspector;