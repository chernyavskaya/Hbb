#source $VO_CMS_SW_DIR/cmsset_default.sh
# shopt -s expand_aliases is needed if you want to use the alias 'cmsenv' created by $VO_CMS_SW_DIR/cmsset_default.sh instead of the less mnemonic eval `scramv1 runtime -sh`

source $VO_CMS_SW_DIR/cmsset_default.sh
source /swshare/psit3/etc/profile.d/cms_ui_env.sh  # for bash

export MYCMSENVDIR=/shome/nchernya/CMSSW_7_4_10/src/
cd $MYCMSENVDIR
eval `scramv1 runtime -sh`
shopt -s expand_aliases 
cmsenv
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap 

export MYBATCHDIR=/shome/nchernya/Hbb/skim_trees/v14/qgd/
cd $MYBATCHDIR

dataset_type=(_double _single)
root=.root

./treeQGL $1 $TMPDIR/$2 $3

#cd $TMPDIR
#echo `pwd`
#cat 5 > $TMPDIR/tet.root
#xrdcp $TMPDIR/tet.root root://t3se01.psi.ch/store/user/nchernya/Hbb/v14/qgd/

echo $TMPDIR/$2${dataset_type[ $3 ]}$root 

cp $TMPDIR/$2${dataset_type[ $3 ]}$root /shome/nchernya/Hbb/
xrdcp $TMPDIR/$2${dataset_type[ $3 ]}$root root://t3se01.psi.ch//store/user/nchernya/Hbb/v14/qgd/
rm  $TMPDIR/$2${dataset_type[ $3 ]}$root 


#$ -o /shome/nchernya/Hbb/skim_trees/batch_logs2/
#$ -e /shome/nchernya/Hbb/skim_trees/batch_logs2/
