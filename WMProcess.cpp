//===========================================
//  Lumina-DE source code
//  Copyright (c) 2012, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#include "WMProcess.h"
#include "LSession.h"

WMProcess::WMProcess() : QProcess(){
  connect(this,SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(processFinished(int, QProcess::ExitStatus)) );
  this->setProcessChannelMode(QProcess::MergedChannels);
  QString log = QString(getenv("XDG_CONFIG_HOME"))+"/lumina-desktop/logs/wm.log";
  if(QFile::exists(log)){ QFile::remove(log); }
  this->setStandardOutputFile(log);
  //ssaver = new QProcess(0);
  inShutdown = false;
}

WMProcess::~WMProcess(){

}

// =======================
//    PUBLIC FUNCTIONS
// =======================
void WMProcess::startWM(){
  inShutdown = false;
  QString cmd = setupWM();
  if(!isRunning()){this->start(cmd); }
}

void WMProcess::stopWM(){
  if(isRunning()){
    inShutdown = true;
    this->kill();
    if(!this->waitForFinished(10000)){ this->terminate(); };
  }else{
    qWarning() << "WM already closed - did it crash?";
  }
}

void WMProcess::restartWM(){
  qDebug() << "Restarting WM";
  if(isRunning()){
    inShutdown = true;
    this->kill();
    if(!this->waitForFinished(5000) ){ this->terminate(); };
    inShutdown = false;
  }
  this->startWM();
}

void WMProcess::updateWM(){
  if(isRunning()){
    qDebug() << "Updating WM";
    ::kill(this->processId(), SIGUSR2); //send fluxbox the signal to reload it's configuration
  }
}
// =======================
//    PRIVATE FUNCTIONS
// =======================
bool WMProcess::isRunning(){
  return (this->state() != QProcess::NotRunning);
}

QString WMProcess::setupWM(){
  QString WM = LSession::handle()->sessionSettings()->value("WindowManager", "fluxbox").toString();
  QString cmd="echo WM Disabled";
  cmd = WM;
  return cmd;
}

// =======================
//     PRIVATE SLOTS
// =======================
void WMProcess::processFinished(int exitcode, QProcess::ExitStatus status){
  if(!inShutdown){
    if(exitcode == 0 && status == QProcess::NormalExit){
      emit WMShutdown();
    }else{
      //restart the Window manager
      qDebug() << "WM Stopped Unexpectedly: Restarting it...";
      this->startWM();
    }
  }
}
