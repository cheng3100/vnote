#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include "scrolldialog.h"

class QGroupBox;
class QPushButton;
class QComboBox;
class QCheckBox;
class QLineEdit;
class QProgressBar;

namespace vnotex
{
    class Notebook;
    class Node;
    class Buffer;

    class ExportDialog : public ScrollDialog
    {
        Q_OBJECT
    public:
        // Current notebook/folder/buffer.
        ExportDialog(const Notebook *p_notebook,
                     const Node *p_folder,
                     const Buffer *p_buffer,
                     QWidget *p_parent = nullptr);

    private:
        enum AdvancedSettings
        {
            General,
            Max
        };

        void setupUI();

        QGroupBox *setupSourceGroup(QWidget *p_parent);

        QGroupBox *setupTargetGroup(QWidget *p_parent);

        QGroupBox *setupAdvancedGroup(QWidget *p_parent);

        QWidget *setupGeneralAdvancedSettings(QWidget *p_parent);

        void setupButtonBox();

        const Notebook *m_notebook = nullptr;

        const Node *m_folder = nullptr;

        const Buffer *m_buffer = nullptr;

        QPushButton *m_exportBtn = nullptr;

        QPushButton *m_openDirBtn = nullptr;

        QPushButton *m_copyContentBtn = nullptr;

        QComboBox *m_sourceComboBox = nullptr;

        QComboBox *m_targetFormatComboBox = nullptr;

        QCheckBox *m_transparentBgCheckBox = nullptr;

        QComboBox *m_renderingStyleComboBox = nullptr;

        QComboBox *m_syntaxHighlightStyleComboBox = nullptr;

        QLineEdit *m_outputDirLineEdit = nullptr;

        QProgressBar *m_progressBar = nullptr;

        QCheckBox *m_recursiveCheckBox = nullptr;

        QVector<QWidget *> m_advancedSettings;
    };
}

#endif // EXPORTDIALOG_H
