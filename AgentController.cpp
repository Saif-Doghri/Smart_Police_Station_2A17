#include "AgentController.h"
#include <QtSql/QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
void AgentController::ajouterAgent(Agent &a){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("INSERT INTO agents(idagent,nomagent,prenomagent,passwordAgent,ageagent,cinagent,date_naissance_agent)"
                     " VALUES(:id,:nom,:prenom,:mdp,:age,:cin,:date_naissance)")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }
    qDebug() <<"Data Received : " <<a.ToString();
    ajout.bindValue(":id",a.getId());
    ajout.bindValue(":nom",a.getNom());
    ajout.bindValue(":prenom",a.getPrenom());
    ajout.bindValue(":age",a.getAge());
    ajout.bindValue(":cin",a.getCIN());
    ajout.bindValue(":mdp",a.getMdp());
    ajout.bindValue(":date_naissance",a.getDate().toString("yyyy-MM-dd"));
    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            qDebug() << "Insertion Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
}

QSqlTableModel* AgentController::afficherAgents(){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("SELECT * FROM agents")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }

    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            qDebug() << "Fetch Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
    return agenttable;
}

void AgentController::modifierAgent(Agent &a, QString id){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("UPDATE agents SET nomagent=:nom,prenomagent=:prenom,passwordAgent=:mdp,ageagent=:age,cinagent=:cin,date_naissance_agent=:date_naissance"
                     " WHERE idagent=:id")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }
    qDebug() <<"Data Received : " <<a.ToString();
    ajout.bindValue(":id",id);
    ajout.bindValue(":nom",a.getNom());
    ajout.bindValue(":prenom",a.getPrenom());
    ajout.bindValue(":age",a.getAge());
    ajout.bindValue(":cin",a.getCIN());
    ajout.bindValue(":mdp",a.getMdp());
    ajout.bindValue(":date_naissance",a.getDate().toString("yyyy-MM-dd"));
    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            qDebug() << "Update Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
}

QSqlTableModel* AgentController::afficherAgent(QString nom){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("SELECT * FROM agents WHERE nomagent=:nom")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }
    ajout.bindValue(":nom",nom);
    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            agenttable->setFilter("nomagent='"+nom+"'");
            qDebug() << "Fetch Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
    return agenttable;
}

void AgentController::supprimerAgent(QString id){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    if(ajout.prepare("DELETE FROM agents WHERE idagent=:id")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }
    ajout.bindValue(":id",id);
    if(ajout.exec()){
        qDebug() << "Success";
        qDebug() << "Delete Complete";
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
}

QSqlTableModel* AgentController::trierAgents(){
    //QSqlDatabase* db=Config::ouvrirConnexion();
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("SELECT * FROM agents")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }

    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            agenttable->sort(0,Qt::AscendingOrder);
            qDebug() << "Sort Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
    return agenttable;
}

QSqlTableModel* AgentController::authenticateAgent(QString nom,QString mdp){
    QSqlQuery ajout;
    QSqlTableModel* agenttable =new QSqlTableModel;
    agenttable->setTable("agents");
    if(ajout.prepare("SELECT * FROM agents")){
            qDebug() << "Query Prepared";
    }else{
        qDebug() << "Failed to Prepare Query";
    }

    if(ajout.exec()){
        qDebug() << "Success";
        if(agenttable->select()){
            agenttable->setFilter("nomagent='"+nom+"' and passwordAgent='"+mdp+"'");
            qDebug() << "Search Complete";
        }
    }else{
        qDebug() << ajout.executedQuery();
        qDebug() <<ajout.lastError().text();
    }
    //Config::fermerConnexion(*db);
    return agenttable;
}