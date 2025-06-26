
import { ManyImportComponent128 } from "./manyImportFile128"
import { ManyImportComponent129 } from "./manyImportFile129"


@Component
export struct ManyImportComponent64 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent128()
            ManyImportComponent129()

        }
    }
}
