#include "backend.h"

#include <QProcess>

Backend::Backend(QObject *parent)
    : QObject(parent) {
  m_busy = false;
}

bool Backend::busy() const {
  return m_busy;
}

void Backend::applyWallpaper(const QString &path) {
  m_busy = true;
  emit busyChanged();

  auto *proc = new QProcess(this);
  proc->start("awww", { "img", path, "--transition-type=random" });

  connect(proc, &QProcess::finished, this, [=, this](int exitCode, QProcess::ExitStatus status) {
    runMatugen(path);
    proc->deleteLater();
  });
}

void Backend::runMatugen(const QString &path) {
  auto *proc = new QProcess(this);
  proc->start("matugen", { "image", path, "-m", "dark", "--source-color-index", "0" });

  connect(proc, &QProcess::finished, this, [=, this](int exitCode, QProcess::ExitStatus status) {
    m_busy = false;
    emit busyChanged();
    proc->deleteLater();
  });
}
