import { BusinessError } from "#external"
export type ErrorCallback = (err: BusinessError) => void;
export type AsyncCallback<T, E = void> = (err: BusinessError<E>, data: T)=> void;