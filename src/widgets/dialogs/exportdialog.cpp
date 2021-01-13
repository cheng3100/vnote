#include "exportdialog.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QProgressBar>

#include <notebook/notebook.h>
#include <notebook/node.h>
#include <buffer/buffer.h>
#include <widgets/widgetsfactory.h>
#include <export/exportdata.h>

using namespace vnotex;

ExportDialog::ExportDialog(const Notebook *p_notebook,
                           const Node *p_folder,
                           const Buffer *p_buffer,
                           QWidget *p_parent)
    : ScrollDialog(p_parent),
      m_notebook(p_notebook),
      m_folder(p_folder),
      m_buffer(p_buffer)
{
    setupUI();
}

void ExportDialog::setupUI()
{
    auto widget = new QWidget(this);
    setCentralWidget(widget);

    auto mainLayout = new QVBoxLayout(widget);

    auto sourceBox = setupSourceGroup(widget);
    mainLayout->addWidget(sourceBox);

    auto targetBox = setupTargetGroup(widget);
    mainLayout->addWidget(targetBox);

    auto advancedBox = setupAdvancedGroup(widget);
    mainLayout->addWidget(advancedBox);

    {
        m_progressBar = new QProgressBar(widget);
        m_progressBar->setRange(0, 0);
        m_progressBar->hide();
        mainLayout->addWidget(m_progressBar);
    }

    setupButtonBox();

    setWindowTitle(tr("Export"));
}

QGroupBox *ExportDialog::setupSourceGroup(QWidget *p_parent)
{
    auto box = new QGroupBox(tr("Source"), this);
    auto layout = WidgetsFactory::createFormLayout(box);

    {
        m_sourceComboBox = WidgetsFactory::createComboBox(p_parent);
        if (m_buffer) {
            m_sourceComboBox->addItem(tr("Current Buffer (%1)").arg(m_buffer->getName()),
                                      static_cast<int>(ExportSource::CurrentBuffer));
        }
        if (m_folder) {
            m_sourceComboBox->addItem(tr("Current Folder (%1)").arg(m_folder->getName()),
                                      static_cast<int>(ExportSource::CurrentFolder));
        }
        if (m_notebook) {
            m_sourceComboBox->addItem(tr("Current Notebook (%1)").arg(m_notebook->getName()),
                                      static_cast<int>(ExportSource::CurrentNotebook));
        }
        layout->addRow(tr("Source:"), m_sourceComboBox);
    }

    {
        // TODO: Source format filtering.
    }

    return box;
}

QGroupBox *ExportDialog::setupTargetGroup(QWidget *p_parent)
{
    auto box = new QGroupBox(tr("Target"), this);
    auto layout = WidgetsFactory::createFormLayout(box);

    {
        m_targetFormatComboBox = WidgetsFactory::createComboBox(p_parent);
        m_targetFormatComboBox->addItem(tr("Markdown"),
                                        static_cast<int>(ExportFormat::Markdown));
        m_targetFormatComboBox->addItem(tr("HTML"),
                                        static_cast<int>(ExportFormat::HTML));
        m_targetFormatComboBox->addItem(tr("PDF"),
                                        static_cast<int>(ExportFormat::PDF));
        m_targetFormatComboBox->addItem(tr("Custom"),
                                        static_cast<int>(ExportFormat::Custom));
        layout->addRow(tr("Format:"), m_targetFormatComboBox);
    }

    {
        m_transparentBgCheckBox = WidgetsFactory::createCheckBox(tr("Use transparent background"), p_parent);
        layout->addRow(m_transparentBgCheckBox);
    }

    {
        m_renderingStyleComboBox = WidgetsFactory::createComboBox(p_parent);
        layout->addRow(tr("Rendering style:"), m_renderingStyleComboBox);
    }

    {
        m_syntaxHighlightStyleComboBox = WidgetsFactory::createComboBox(p_parent);
        layout->addRow(tr("Syntax highlight style:"), m_syntaxHighlightStyleComboBox);
    }

    {
        auto outputLayout = new QHBoxLayout();

        m_outputDirLineEdit = WidgetsFactory::createLineEdit(p_parent);
        outputLayout->addWidget(m_outputDirLineEdit);

        auto browseBtn = new QPushButton(tr("Browse"), p_parent);
        outputLayout->addWidget(browseBtn);

        layout->addRow(tr("Output directory:"), outputLayout);
    }

    return box;
}

QGroupBox *ExportDialog::setupAdvancedGroup(QWidget *p_parent)
{
    auto box = new QGroupBox(tr("Advanced"), this);
    auto layout = new QVBoxLayout(box);

    m_advancedSettings.resize(AdvancedSettings::Max);

    m_advancedSettings[AdvancedSettings::General] = setupGeneralAdvancedSettings(box);
    layout->addWidget(m_advancedSettings[AdvancedSettings::General]);

    return box;
}

QWidget *ExportDialog::setupGeneralAdvancedSettings(QWidget *p_parent)
{
    QWidget *widget = new QWidget(p_parent);
    auto layout = WidgetsFactory::createFormLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);

    {
        m_recursiveCheckBox = WidgetsFactory::createCheckBox(tr("Process sub-folders"), widget);
        layout->addRow(m_recursiveCheckBox);
    }

    return widget;
}

void ExportDialog::setupButtonBox()
{
    setDialogButtonBox(QDialogButtonBox::Close);

    auto box = getDialogButtonBox();

    m_exportBtn = box->addButton(tr("Export"), QDialogButtonBox::ActionRole);
    m_openDirBtn = box->addButton(tr("Open Directory"), QDialogButtonBox::ActionRole);
    m_copyContentBtn = box->addButton(tr("Copy Content"), QDialogButtonBox::ActionRole);
    m_copyContentBtn->setToolTip(tr("Copy exported file content"));
}
