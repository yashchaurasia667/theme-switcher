#include "wallpapermodel.h"
#include <qhash.h>

#include <QDirIterator>

WallpaperModel::WallpaperModel(QObject *parent)
    : QAbstractListModel(parent) {
  wallpaper_dir = QDir::homePath() + "/Pictures/wall/";

  QDirIterator it(wallpaper_dir, filter, QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext()) {
    m_paths.push_back(it.next());
  }
}

int WallpaperModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return static_cast<int>(m_paths.size());
}

QVariant WallpaperModel::data(const QModelIndex &index, int role) const {
  if (index.isValid() && index.row() < m_paths.size()) {
    if (role == FilePathRole)
      return QVariant{ m_paths.at(index.row()) };
  }
  return QVariant{};
}

QHash<int, QByteArray> WallpaperModel::roleNames() const {
  return {
    {FilePathRole, "filePath"}
  };
}
