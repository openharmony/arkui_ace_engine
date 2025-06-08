
import { ManyImportComponent194 } from "./manyImportFile194"
import { ManyImportComponent195 } from "./manyImportFile195"


@Component
export struct ManyImportComponent97 {
    @State message: string = 'Hello ArkTS'

    build() {
        Column() {
            Text(this.message)
            ManyImportComponent194()
            ManyImportComponent195()

        }
    }
}
