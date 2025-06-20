
import { ManyImportComponent106 } from "./manyImportFile106"
import { ManyImportComponent107 } from "./manyImportFile107"


@Component
export struct ManyImportComponent53 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent106()
            ManyImportComponent107()

        }
    }
}
