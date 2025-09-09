
import { ManyImportComponent118 } from "./manyImportFile118"
import { ManyImportComponent119 } from "./manyImportFile119"


@Component
export struct ManyImportComponent59 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent118()
            ManyImportComponent119()

        }
    }
}
