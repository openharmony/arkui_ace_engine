
import { ManyImportComponent54 } from "./manyImportFile54"
import { ManyImportComponent55 } from "./manyImportFile55"


@Component
export struct ManyImportComponent27 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent54()
            ManyImportComponent55()

        }
    }
}
