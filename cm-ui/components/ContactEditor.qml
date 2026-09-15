import QtQuick 2.9
import CM 1.0
import assets 1.0

Panel {
    property QtObject contentFrame
    property Client client
    id: contactsEditorRoot
    contentComponent:
        Column {
        id: column
        spacing: Style.sizeControlSpacing
        Repeater {
            id: contactsView
            model: client.ui_contacts
            delegate:
                ContactDelegate {
                contentFrame: contactsEditorRoot.contentFrame
                width: contactsEditorRoot.width
                contact: modelData
            }
        }
        FormButton {
            iconCharacter: "plus"
            description: "Add Contact"
            onFormButtonClicked: {
                client.addContact();
            }
        }
    }
}
