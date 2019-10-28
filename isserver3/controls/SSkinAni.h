#pragma once

#include <interface/srender-i.h>
namespace SOUI
{
    class SSkinAni : public SSkinObjBase
    {
        SOUI_CLASS_NAME(SSkinAni,L"skinani")
    public:
        SSkinAni():m_nFrames(0),m_iFrame(0)
        {

        }

        virtual ~SSkinAni()
        {
        }

		virtual long GetFrameDelay(int iFrame=-1) = 0;

		virtual int LoadFromFile(LPCTSTR pszFileName)=0;

        virtual int LoadFromMemory(LPVOID pBits,size_t szData)=0;

		/**
        * ActiveNextFrame
        * @brief    激活下一帧
        * @return   void 
        * Describe  
        */    
        void ActiveNextFrame()
        {
            if(m_nFrames>1)
            {
                m_iFrame++;
                if(m_iFrame==m_nFrames) m_iFrame=0;
                SelectActiveFrame(m_iFrame);
            }
        }

        /**
        * SelectActiveFrame
        * @brief    激活指定帧
        * @param    int iFrame --  帧号
        * @return   void
        * Describe  
        */    
        void SelectActiveFrame(int iFrame) const
        {
            if(m_nFrames>1 && iFrame<m_nFrames)
            {
                m_iFrame = iFrame;
            }
        }

	protected:
		int m_nFrames;
        mutable int m_iFrame;

    };

}