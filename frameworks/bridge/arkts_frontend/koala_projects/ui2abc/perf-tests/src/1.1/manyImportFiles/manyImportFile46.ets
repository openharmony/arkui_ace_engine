
import { ManyImportComponent92 } from "./manyImportFile92"
import { ManyImportComponent93 } from "./manyImportFile93"


@Component
export struct ManyImportComponent46 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent92()
            ManyImportComponent93()

        }
    }
}
