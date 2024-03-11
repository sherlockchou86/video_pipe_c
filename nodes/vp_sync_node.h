
#include "vp_node.h"

namespace vp_nodes {
    // sync mode
    enum class vp_sync_mode {
        // merge target (vp_frame_target/vp_frame_face_target/...) collections between the 1st vp_frame_meta and the 2nd vp_frame_meta
        // mainly used for sync primary infer data which created by those derived from vp_primary_infer_node
        MERGE = 0,
        // update properties of target(vp_frame_target/vp_frame_face_target/...) from the 1st vp_frame_meta to 2nd vp_frame_meta
        // mainly used for sync secondary infer data which generated by those derived from vp_secondary_infer_node， could also be used for sync other properties like tracking ids.
        UPDATE = 1
    };

    // sync data(hold by vp_frame_meta) for the same frame in the same channel
    // mainly be used to sync infer results between parallel nodes which have been splited by vp_split_node before in the same channel
    // note: it could also sync vp_control_meta, just filter the same control meta by control uid.
    class vp_sync_node: public vp_node
    {
    private:
        // do sync work
        void sync(std::shared_ptr<vp_objects::vp_frame_meta> des, std::shared_ptr<vp_objects::vp_frame_meta> src);
        // sync mode
        vp_sync_mode mode = vp_sync_mode::MERGE;
        // push to downstream directly after waiting a period of time(milliseconds), because we can not wait infinitely
        int timeout = 40;  // wait for 40ms for each frame since 25fps is normal for video stream

        /* multi-channel supported*/
        std::map<int, int> all_indexs_last_syned;
        std::map<int, std::string> all_control_uids_last_synced;
        std::map<int, std::vector<std::shared_ptr<vp_objects::vp_meta>>> all_meta_waiting_for_sync;
    protected:
        // re-implementation
        virtual std::shared_ptr<vp_objects::vp_meta> handle_frame_meta(std::shared_ptr<vp_objects::vp_frame_meta> meta) override;
        // re-implementation
        virtual std::shared_ptr<vp_objects::vp_meta> handle_control_meta(std::shared_ptr<vp_objects::vp_control_meta> meta) override;
    public:
        vp_sync_node(std::string node_name, vp_sync_mode mode = vp_sync_mode::MERGE, int timeout = 40);
        ~vp_sync_node();
    };
}