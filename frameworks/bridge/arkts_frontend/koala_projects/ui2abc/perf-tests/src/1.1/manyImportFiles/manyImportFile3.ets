
import { ManyImportComponent6 } from "./manyImportFile6"
import { ManyImportComponent7 } from "./manyImportFile7"


@Component
export struct ManyImportComponent3 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent6()
            ManyImportComponent7()

        }
    }
}
