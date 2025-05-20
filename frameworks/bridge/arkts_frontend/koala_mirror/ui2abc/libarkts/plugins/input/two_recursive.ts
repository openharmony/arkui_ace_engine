import { One } from "./one_recursive"

export interface Two {
    one(): One {
        throw new Error("")
    }
}

