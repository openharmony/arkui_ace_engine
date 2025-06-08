
import { ManyImportComponent26 } from "./manyImportFile26"
import { ManyImportComponent27 } from "./manyImportFile27"


@Component
export struct ManyImportComponent13 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent26()
            ManyImportComponent27()

        }
    }
}
