
import { ManyImportComponent56 } from "./manyImportFile56"
import { ManyImportComponent57 } from "./manyImportFile57"


@Component
export struct ManyImportComponent28 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent56()
            ManyImportComponent57()

        }
    }
}
