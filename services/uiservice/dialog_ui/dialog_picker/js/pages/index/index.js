import router from '@system.router'
import resourceManager from '@ohos.resourceManager';

export default {
    data: {
        shareHapList: [],
        lineNums: 6,
        iconBorad: "0.25vp solid #000000",
        viewStyle: {
            textVisible: "visible",
            copyVisible: "hidden",
            printVisible: "hidden",
            textMainHeight: "19vp",
            icon: "",
            iconBoard: "",
            format: "png",
            button1: "",
            button2: "",
        }
    },
    onInit() {
        this.getViewStyle();
        let shareHap = [];
        for (let i = 0; i < this.hapList.length; i++) {
            shareHap.push(this.hapList[i]);
            if (i % this.lineNums == this.lineNums - 1 || i == this.hapList.length - 1) {
                this.shareHapList.push(shareHap);
                shareHap = [];
            }
        }
    },
    onShare: function (item) {
        let param = item.bundle + ";" + item.ability;
        callNativeHandler('SHARE_EVENT', param);
    },
    changeSize: function (param) {
        callNativeHandler('CLOSE_EVENT', "");
    },
    onBack: function () {
        callNativeHandler('CLOSE_EVENT', "");
    },
    getViewStyle() {
        this.viewStyle.button1 = this.$t('strings.btnCopy');
        this.viewStyle.button2 = this.$t('strings.btnPrint');
        let defaultIcon = "";
        let fileNums = this.previewCard.fileList == null ? 0 : this.previewCard.fileList.length;
        if (this.previewCard.type == "text/plain") {
            this.viewStyle.textVisible = "hidden"
            this.viewStyle.textMainHeight = "38vp";
            defaultIcon = "ic_documents";
        } else if (this.previewCard.type == "text/html") {
            defaultIcon = "ic_html";
            this.previewCard.subText = this.$t('strings.uri') + this.previewCard.subText;
        } else if (fileNums == 0) {
            defaultIcon = "ic_unknown";
            if (this.previewCard.type == null) {
                if (this.previewCard.subText != null) {
                    defaultIcon = "ic_html";
                    this.previewCard.subText = this.$t('strings.uri') + this.previewCard.subText;
                } else if (this.previewCard.mainText != null) {
                    this.viewStyle.textVisible = "hidden"
                    this.viewStyle.textMainHeight = "38vp";
                    defaultIcon = "ic_documents";
                }
            }
            if (defaultIcon == "ic_unknown") {
                this.previewCard.mainText = this.$t('strings.unknown');
                this.previewCard.subText = this.$t('strings.fileSize') + " KB";
            }
        } else if (fileNums == 1) {
            this.previewCard.mainText = this.previewCard.fileList[0].name;
            this.previewCard.subText = this.$t('strings.fileSize') + Math.round(this.previewCard.fileList[0].size / 1024) + "KB";
            if (this.previewCard.type.indexOf("image/") != -1) {
                defaultIcon = "ic_image";
            } else if (this.previewCard.type.indexOf("application/apk") != -1) {
                defaultIcon = "ic_apk";
            } else if (this.previewCard.type.indexOf("application/pdf") != -1) {
                defaultIcon = "ic_pdf";
            } else if (this.previewCard.type.indexOf("application/doc") != -1) {
                defaultIcon = "ic_doc";
            } else if (this.previewCard.type.indexOf("application/ppt") != -1) {
                defaultIcon = "ic_pptx";
            } else if (this.previewCard.type.indexOf("application/xls") != -1) {
                defaultIcon = "ic_xls";
            } else if (this.previewCard.type.indexOf("application/ics") != -1) {
                defaultIcon = "ic_calendar";
            } else if (this.previewCard.type.indexOf("application/vcf") != -1) {
                defaultIcon = "ic_contacts";
            } else if (this.previewCard.type.indexOf("video/") != -1) {
                defaultIcon = "ic_video";
            } else if (this.previewCard.type.indexOf("audio/") != -1) {
                defaultIcon = "ic_mp3";
            } else {
                defaultIcon = "ic_unknown";
            }
            if (this.previewCard.mainText == "") {
                this.previewCard.mainText = this.$t('strings.unknown');;
            }
        } else {
            defaultIcon = "ic_file_multiple";
            if (this.previewCard.type.indexOf("*") != -1) {
                this.previewCard.mainText = fileNums + this.$t('strings.sameFile');
            } else {
                this.previewCard.mainText = fileNums + this.$t('strings.unSameFile');
            }
            let totalSize = 0;
            for (let i = 0; i < fileNums; i++) {
                if (this.previewCard.fileList[i].size != null) {
                    totalSize += this.previewCard.fileList[i].size;
                }
            }
            this.previewCard.subText = this.$t('strings.totalSize') + Math.round(totalSize / 1024) + "KB";
        }
        this.viewStyle.icon = "common/" + defaultIcon + "." + this.viewStyle.format;
    }
}
