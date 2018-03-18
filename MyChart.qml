import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import "./config.js" as Config
Item {
    property variant allConfig
    property variant currentConfig
    property alias chart: chartID
    property alias periodBox: periodBox
    Background {
        anchors.fill: parent
    }
    ComboBox {
            id: periodBox
            objectName: "periodBoxObject"
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.8
            height: 40
            opacity: 0.5
            model: ["Today", "3 days","Week", "Month","Year"]
            onActivated: {
                Interact.onUpdateChartSignal("",currentIndex);

            }
    }
    Loader {
        source: "qrc:/Qchart2.qml"
        id:chartID
        visible: true
        height: parent.height-periodBox.height
        width: parent.width
        anchors.top: periodBox.bottom
        anchors.bottomMargin: 40
        onLoaded: {
            if(currentConfig != null) {
            chartID.item.chartData = currentConfig.data
            chartID.item.chartOptions = currentConfig.options
            chartID.item.chartType = currentConfig.type
            chartID.item.requestPaint()
            }
        }
        onSourceChanged:
            gc()
    }
    function updater() {
        currentConfig = null;
        currentConfig = Config.config2()[0]
        chartID.item._chart.destroy()
        chartID.source = ""
        chartID.source = "qrc:/Qchart2.qml"
    }
}

