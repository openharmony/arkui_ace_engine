
import { ManyImportComponent134 } from "./manyImportFile134"
import { ManyImportComponent135 } from "./manyImportFile135"


@Component
export struct ManyImportComponent67 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent134()
            ManyImportComponent135()

        }
    }
}
