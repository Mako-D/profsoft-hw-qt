import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQml 2.15
import QtQuick.Window 2.2

Window {
    id: appWindow
    visible: true
    width: 300
    height: 600

    // === GAME SETTINGS ===
    readonly property var buttonSizeWidth: 20                   // pixels
    readonly property var buttonSizeHeight: 20                  // pixels
    readonly property var buttonTimeToMoveMin: 100              // msec
    readonly property var buttonTimeToMoveMax: 400              // msec
    readonly property var buttonStandardStep: 2                 // pixels
    readonly property var buttonMultiplyStepByHovered: 2        // value
    readonly property var buttonHeightSpawn: 100                // pixels
    readonly property var buttonTimeToSpawnMin: 100             // msec
    readonly property var buttonTimeToSpawnMax: 1000            // msec
    readonly property var buttonTimeToFirstSpawn: 1             // msec
    // =====================

    function getRandomInterval(min, max)
    {
        return Math.random() * (max - min) + min
    }
    function getRandom(max)
    {
        return Math.random() * max
    }

    Component {
        id: gameplayButton
        Button {
            id: btn
            width: buttonSizeWidth
            height: buttonSizeHeight

            onClicked: destroy()

            Timer {
                interval: getRandomInterval(buttonTimeToMoveMin, buttonTimeToMoveMax)
                repeat: true
                running: true
                onTriggered: {
                    btn.y += buttonStandardStep * ( btn.hovered ? buttonMultiplyStepByHovered : 1 )
                    if(btn.y > appWindow.height - btn.height)
                    {
                        appWindow.color = "red"
                        appWindow.title = "You Loose!"
                        btn.destroy()
                    }
                }
            }
        }
    }

    function spawnGameplayButton() {
        gameplayButton.createObject(appWindow, {
            x: getRandom(appWindow.width),
            y: getRandom(buttonHeightSpawn)
        });
        timerSpawn.interval = getRandomInterval(buttonTimeToSpawnMin, buttonTimeToSpawnMax)
    }

    Timer {
        id: timerSpawn
        interval: buttonTimeToFirstSpawn
        onTriggered: appWindow.spawnGameplayButton()
        repeat: true
        running: true
    }
}
