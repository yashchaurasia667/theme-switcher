#include "backend.h"
#include <qprocess.h>

#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

const QStringList Backend::kRoles = {
  "primary", "secondary", "tertiary", "error",
  "background", "surface", "surface_variant",
  "outline", "inverse_primary", "source_color"
};

Backend::Backend(QObject *parent)
    : QObject(parent) {
  m_busy = false;
}

bool Backend::busy() const {
  return m_busy;
}

QStringList Backend::palette() const {
  return m_palette;
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

void Backend::generatePalette(const QString &path) {
  auto *proc = new QProcess(this);
  proc->start("matugen", { "image", path, "--dry-run", "--source-color-index", "0", "--json", "hex" });

  connect(proc, &QProcess::finished, this, [=, this](int, QProcess::ExitStatus) {
      QByteArray output = proc->readAllStandardOutput();
      QJsonDocument doc = QJsonDocument::fromJson(output);
      if(!doc.isObject()) {
      std::cout << "output is not a json object" << std::endl;
      return;
      }

      QJsonObject colors = doc.object().value("colors").toObject();
      m_palette.clear();

      for(const QString &role: kRoles) {
      QString hex = colors.value(role).toObject()
      .value("dark").toObject()
      .value("color").toString();
      if(!hex.isEmpty())
      m_palette.append(hex);
      }

      emit paletteUpdated();
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
