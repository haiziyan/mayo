/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#pragma once

#include "application.h"
#include "application_item.h"
#include "application_item_selection_model.h"
#include <QtWidgets/QMainWindow>
#include <memory>
class QFileInfo;

namespace Mayo {

class Document;
class GuiDocument;
class WidgetGuiDocument;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void openDocumentsFromList(const QStringList& listFilePath);

    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    void operationFinished(bool ok, const QString& msg);
    void currentDocumentIndexChanged(int docIdx);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void newDocument();
    void openDocuments();
    void importInCurrentDoc();
    void exportSelectedItems();
    void quitApp();
    void toggleCurrentDocOriginTrihedron();
    void zoomInCurrentDoc();
    void zoomOutCurrentDoc();
    void editOptions();
    void saveImageView();
    void inspectXde();
    void toggleFullscreen();
    void toggleLeftSidebar();
    void aboutMayo();
    void reportbug();

    void onApplicationItemSelectionChanged();
    void onOperationFinished(bool ok, const QString& msg);
    void onHomePageLinkActivated(const QString& link);
    void onGuiDocumentAdded(GuiDocument* guiDoc);
    void onWidgetFileSystemLocationActivated(const QFileInfo& loc);
    void onLeftContentsPageChanged(int pageId);
    void onCurrentDocumentIndexChanged(int idx);

    void closeCurrentDocument();
    void closeDocument(WidgetGuiDocument* widget);
    void closeDocument(int docIndex);
    void closeAllDocumentsExceptCurrent();
    void closeAllDocuments();

    void runImportTask(
            Document* doc,
            Application::PartFormat format,
            const QString& filepath);
    void runExportTask(
            Span<const ApplicationItem> appItems,
            Application::PartFormat format,
            const Application::ExportOptions& opts,
            const QString& filepath);

    void updateControlsActivation();

    int currentDocumentIndex() const;
    void setCurrentDocumentIndex(int idx);

    WidgetGuiDocument* widgetGuiDocument(int idx) const;
    WidgetGuiDocument* currentWidgetGuiDocument() const;
    QWidget* findLeftHeaderPlaceHolder() const;
    QWidget* recreateLeftHeaderPlaceHolder();
    QMenu* createMenuModelTreeSettings();
    QMenu* createMenuRecentFiles();

    class Ui_MainWindow* m_ui = nullptr;
    Qt::WindowStates m_previousWindowState = Qt::WindowNoState;
    QStringList m_listRecentFile;
    std::unique_ptr<PropertyOwnerSignals> m_ptrCurrentNodeProperties;
};

} // namespace Mayo
