#pragma once
#include <qqml.h>
#include <qtmetamacros.h>

#include <QObject>

// Q_PROPERTY(Type name READ getterName NOTIFY signalName)
class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)
  Q_PROPERTY(QStringList palette READ palette NOTIFY paletteUpdated)

public:
  explicit Backend(QObject *parent = nullptr);
  Q_INVOKABLE void applyWallpaper(const QString &path);
  Q_INVOKABLE void generatePalette(const QString &path);
  bool busy() const;
  QStringList palette() const;

private:
  bool m_busy = false;
  QStringList m_palette;
  static const QStringList kRoles;

  void runMatugen(const QString &path);
signals:
  void busyChanged();
  void paletteUpdated();
};
