
import { ManyImportComponent90 } from "./manyImportFile90"
import { ManyImportComponent91 } from "./manyImportFile91"


@Component
export struct ManyImportComponent45 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent90()
            ManyImportComponent91()

        }
    }
}
