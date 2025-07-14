
import { ManyImportComponent100 } from "./manyImportFile100"
import { ManyImportComponent101 } from "./manyImportFile101"


@Component
export struct ManyImportComponent50 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent100()
            ManyImportComponent101()

        }
    }
}
