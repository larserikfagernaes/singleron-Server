#include "helloDragon/logicUnits/DatabaseConnector.hpp"
#include "helloDragon/logicUnits/QueryFactory.hpp"
#include "helloDragon/logicUnits/Filewriter.hpp"
#include "helloDragon/logicUnits/Authentication.hpp"
#include "helloDragon/helpers/LEOptional.hpp"
#include "helloDragon/logicUnits/QueryFactory.hpp"
#include "helloDragon/helpers/RInstance.hpp"
#include "RequestController.h"
#include <iostream>
#include <RInside.h>                            // for the embedded R via RInside

using namespace std;

#include <iostream>

void RequestController::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    string username = req.get()->getParameter("username");
    string hashed_pass = req.get()->getParameter("password");
    string filepath = req.get()->getParameter("filepath");
    
    DatabaseConnector dbConnection("localhost", "root", "root", "singleron_auth");
    dbConnection.testConnection();
    Authentication auth(dbConnection.getConnection());
    Filewriter filewriter(&auth);
    
    std::string str =
    "suppressMessages(require(Seurat));"
    "suppressMessages(require(Seurat));"
    "cbmc.rna <- as.sparse(read.csv(file = \"/Users/LarsErik/Skole/tsinghua/spring/AdvancedML/semesterProject/mlOnSingleCellSequencing/data/SimulatedWOBatchEffectv2/counts.csv\", sep = \",\", header = TRUE, row.names = 1));"
    "pbmc <- CreateSeuratObject(counts = cbmc.rna, project = \"IMMUNE_CTRL\", min.cells = 3, min.features = 200);"
    "pbmc[[\"percent.mt\"]] <- PercentageFeatureSet(pbmc, pattern = \"^MT-\");"
    "pbmc <- subset(pbmc, subset = nFeature_RNA > 200 & nFeature_RNA < 2500);"
    "pbmc <- NormalizeData(pbmc, normalization.method = \"LogNormalize\", scale.factor = 10000);"
    "pbmc <- FindVariableFeatures(pbmc, selection.method = \"vst\", nfeatures = 2000);"
    "all.genes <- rownames(pbmc);"
    "pbmc <- ScaleData(pbmc, features = all.genes);"
    "pbmc <- RunPCA(pbmc, features = VariableFeatures(object = pbmc));"
    "pbmc <- FindNeighbors(pbmc, dims = 1:10);"
    "pbmc <- FindClusters(pbmc, resolution = 0.5);"
    "pbmc$seurat_clusters;";
    
    
    
    Rcpp::IntegerVector groups = RInside::instance().parseEval(str);

    std::string output_string;

//    for (int i = 0; i < groups.size(); i++){
//        output_string += std::to_string(i) + " = " + std::to_string(groups[i]) + "\n";
//    }

    filewriter.encryptAndWriteData(output_string, "randomFile.txt", "r2p");
    LEOptional<string> decryptedOutput = filewriter.decryptData("hahajjjjj", "hahajjjjj", "randomFile.txt", "r2p");
    if (decryptedOutput.hasValue()){
        std::cout << "we have value!" ;
        std::cout << decryptedOutput.getData();
    }
//
    //write your application logic here
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("Hello World1!");
    callback(resp);
}
