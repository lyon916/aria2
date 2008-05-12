/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_DEFAULT_BT_REQUEST_FACTORY_H_
#define _D_DEFAULT_BT_REQUEST_FACTORY_H_

#include "BtRequestFactory.h"

namespace aria2 {

class BtContext;
class PieceStorage;
class Peer;
class BtMessageDispatcher;
class BtMessageFactory;
class Piece;

class DefaultBtRequestFactory : public BtRequestFactory {
private:
  int32_t cuid;
  SharedHandle<BtContext> btContext;
  SharedHandle<PieceStorage> pieceStorage;
  SharedHandle<Peer> peer;
  WeakHandle<BtMessageDispatcher> dispatcher;
  WeakHandle<BtMessageFactory> messageFactory;
  std::deque<SharedHandle<Piece> > pieces;
public:
  DefaultBtRequestFactory();

  virtual ~DefaultBtRequestFactory();

  virtual void addTargetPiece(const SharedHandle<Piece>& piece);

  virtual void removeTargetPiece(const SharedHandle<Piece>& piece);

  virtual void removeAllTargetPiece();

  virtual size_t countTargetPiece() {
    return pieces.size();
  }

  virtual void removeCompletedPiece();

  virtual void doChokedAction();

  virtual void createRequestMessages
  (std::deque<SharedHandle<BtMessage> >& requests, size_t max);

  virtual void createRequestMessagesOnEndGame
  (std::deque<SharedHandle<BtMessage> >& requests, size_t max);

  std::deque<SharedHandle<Piece> >& getTargetPieces();

  void setCuid(int32_t cuid)
  {
    this->cuid = cuid;
  }

  void setBtContext(const SharedHandle<BtContext>& btContext);

  void setPeer(const SharedHandle<Peer>& peer);

  void setBtMessageDispatcher(const WeakHandle<BtMessageDispatcher>& dispatcher);

  void setBtMessageFactory(const WeakHandle<BtMessageFactory>& factory);
};

typedef SharedHandle<DefaultBtRequestFactory> DefaultBtRequestFactoryHandle;

} // namespace aria2

#endif // _D_DEFAULT_BT_REQUEST_FACTORY_H_
