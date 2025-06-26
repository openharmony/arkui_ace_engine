
import { ManyImportComponent116 } from "./manyImportFile116"
import { ManyImportComponent117 } from "./manyImportFile117"


@Component
export struct ManyImportComponent58 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent116()
            ManyImportComponent117()

        }
    }
}
