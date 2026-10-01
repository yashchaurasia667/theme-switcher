#pragma once

#include <qqml.h>

#include <QAbstractListModel>
#include <QDir>

class WallpaperModel : public QAbstractListModel {
  Q_OBJECT
  QML_ELEMENT

public:
  enum Roles {
    FilePathRole = Qt::UserRole + 1,
  };

  explicit WallpaperModel(QObject *parent = nullptr);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  // ~WallpaperModel();

private:
  QStringList filter = { "*.png", "*.jpg", "*.jpeg" };

  QString wallpaper_dir;
  QVector<QString> m_paths;
};
