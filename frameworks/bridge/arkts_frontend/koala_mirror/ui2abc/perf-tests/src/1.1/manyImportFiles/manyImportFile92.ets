
import { ManyImportComponent184 } from "./manyImportFile184"
import { ManyImportComponent185 } from "./manyImportFile185"


@Component
export struct ManyImportComponent92 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent184()
            ManyImportComponent185()

        }
    }
}
