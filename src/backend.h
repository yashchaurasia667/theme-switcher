#pragma once
#include <qqml.h>

#include <QObject>

class Backend : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:
  explicit Backend(QObject *parent = nullptr);
  // Q_PROPERTY(Type name READ getterName NOTIFY signalName)
  Q_INVOKABLE void applyWallpaper(const QString &path);
  bool busy() const;

private:
  bool m_busy = false;
  void runMatugen(const QString &path);
signals:
  void busyChanged();
};
