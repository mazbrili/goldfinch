#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mycontentmodel.h"
#include "mylistmodel.h"
#include "treeviewcontent.h"
#include "listview.h"
#include "treeviewaudio.h"
#include "mediaupdate.h"
#include "database.h"
#include "listitemdelegate.h"
#include "treeitemdelegate.h"
#include "player.h"
#include "playercontrols.h"
#include "setting.h"
#include "widgetplaylist.h"
#include "widgetimageinfo.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     Player *player(){return mPlayer;}
signals:
    void iconsChanged();

private:
    Ui::MainWindow *ui;
    //!
    void changeEvent(QEvent *event);
    //!
    void changeStyleSheet();
    //!
    QMap<QString,QString>mMap;
    //! موديول قائمة النفاصبل
    MyContentModel *mMyTreeModel;
    //! موديول القائمة الايقونات
    MyListModel *mMyListModel;
    //! شجرة عرض التفاصبل
    TreeViewContent *mTVContent;
    //!
    TreeViewAudio *mTVAudio;
    //!
    ListView *mListView;
    //!  حاوي القائمة وادات تجرير القائمة
    WidgetPlayList *mWPlayList;
    //! قاغدة البيانات
    DataBase *mDataBase;
    //! تحرير مظهر الايقونات في معرض القائمة
    ListItemDelegate *mLIDelegate;
    //!
    TreeItemDelegate *mTItemDelegate;
    //! وحدة القراءة
    Player *mPlayer;
    //! التحكم في ازرار القراءة
    PlayerControls *controls;
    //!
    WidgetImageInfo *mImageInfo;
    //! تحديث المقطوعات من الجهاز
    MediaUpdate *mMediaUpdate;
    //!
    Setting *mSetting;
    //!
    QAction *mActSwich;
    //!
    QSlider *mSliderIconSize;
    //!
    int mIconSize=94;
    //!
    QString mcoloor;

private slots:
    //!
    void switchViewMode(bool mini);
    //!
    void chargeRecent();
    //! تحميل الايقونات
    void setupIcons();
    //! اعادة التحميل بعد اكتمال التحديث
    void rechargeAlbums();
    //! عرض نسبة التقدم
    void progressShow(int max);
    //! نسبة التقدم
    void progressSetValue(int value);
    //! عرض مسار الالبومات
    void changeStatusPathText();
    //! تغيير مسار الالبومات
    void setPathAlbum(int index);
    //! اضاغة مسارات جديدة لتحميل الالبومات
    //!
    void setIconSize(int value);
    //!
    void setwTitle(const QString &title){setWindowTitle(title);}
    //!
    void chargeListItemes();
    void setlabelImage();
    //!
    void on_actionaddDir_triggered();
    //!
    void treeViewContentActivated(const QModelIndex &index);
    //!
    void listViewActivated(const QModelIndex &index);
    //!
    void on_tb_paneContent_toggled(bool checked);
    //!
    void on_tb_panePlaylist_toggled(bool checked);
    //!
    void on_tb_addAlbum_clicked();
    //!
    void on_tb_playAlbum_clicked();
    //!
    void onChangeImageAlbum(int row);
//!
   void changeImageAlbum(int id ,const QString Name);
//!
      void on_tb_imgAlbum_clicked();

    //!
    void onFavoritAlbum(int row, bool favo);
    //!
    void onAddAlbum(int row);
    //!
    void onPlayAlbum(int row);
    //!
    void on_tb_favoritAlbum_clicked();
    //!
    void treeAudioClicked(const QModelIndex &index);
    //!
    void treeAudioActivated(const QModelIndex &index);
    //!
    void editCurIndex(const QString &path);
    //!
    void on_actionopen_triggered();


};

#endif // MAINWINDOW_H